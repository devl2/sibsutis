import React, { useState, useEffect } from 'react';
import { BrowserRouter as Router, Routes, Route, Link, Navigate } from 'react-router-dom';
import { Formik, Form, Field, ErrorMessage } from 'formik';
import * as Yup from 'yup';
import CommentsApp from './components/CommentsApp';

const App = () => {
  const [commentsData, setCommentsData] = useState([]);
  const [postsData, setPostsData] = useState([]);
  const [albumsData, setAlbumsData] = useState([]);
  const [todosData, setTodosData] = useState([]);
  const [usersData, setUsersData] = useState([]);
  const [loading, setLoading] = useState(true);

  useEffect(() => {
    const fetchAllData = async () => {
      try {
        const [comments, posts, albums, todos, users] = await Promise.all([
          fetch('https://jsonplaceholder.typicode.com/comments?_limit=10').then(res => res.json()),
          fetch('https://jsonplaceholder.typicode.com/posts?_limit=10').then(res => res.json()),
          fetch('https://jsonplaceholder.typicode.com/albums?_limit=10').then(res => res.json()),
          fetch('https://jsonplaceholder.typicode.com/todos?_limit=10').then(res => res.json()),
          fetch('https://jsonplaceholder.typicode.com/users?_limit=10').then(res => res.json())
        ]);
        
        setCommentsData(comments);
        setPostsData(posts);
        setAlbumsData(albums);
        setTodosData(todos);
        setUsersData(users);
      } catch (err) {
        console.error('Ошибка загрузки данных:', err);
      } finally {
        setLoading(false);
      }
    };

    fetchAllData();
  }, []);

  const handleEdit = async (url, rowIndex, field, value, updatedItem, setData) => {
    try {
      const response = await fetch(`${url}/${updatedItem.id}`, {
        method: 'PATCH',
        body: JSON.stringify({ [field]: value }),
        headers: {
          'Content-type': 'application/json; charset=UTF-8',
        },
      });

      if (!response.ok) throw new Error('Ошибка сервера');

      const serverData = await response.json();
      
      setData(prev => prev.map((item, idx) => 
        idx === rowIndex ? { ...item, ...serverData } : item
      ));
    } catch (err) {
      console.error('Ошибка обновления:', err);
      throw err;
    }
  };

  const handleDelete = async (url, indexes, data, setData) => {
    try {
      const deletePromises = indexes.map(index => 
        fetch(`${url}/${data[index].id}`, {
          method: 'DELETE',
        })
      );

      await Promise.all(deletePromises);
      setData(prev => prev.filter((_, index) => !indexes.includes(index)));
    } catch (err) {
      console.error('Ошибка удаления:', err);
      throw err;
    }
  };

  if (loading) return <div>Загрузка...</div>;

  return (
    <Router>
      <div style={{ display: 'flex', minHeight: '100vh' }}>
        <div style={{ 
          width: '200px', 
          background: '#f0f0f0', 
          padding: '20px',
          boxShadow: '2px 0 5px rgba(0,0,0,0.1)'
        }}>
          <h2 style={{ marginTop: 0 }}>Навигация</h2>
          <nav style={{ display: 'flex', flexDirection: 'column' }}>
            <Link to="/comments" style={navLinkStyle}>Комментарии</Link>
            <Link to="/posts" style={navLinkStyle}>Посты</Link>
            <Link to="/albums" style={navLinkStyle}>Альбомы</Link>
            <Link to="/todos" style={navLinkStyle}>Задачи</Link>
            <Link to="/users" style={navLinkStyle}>Пользователи</Link>
          </nav>
        </div>

        <div style={{ flex: 1, padding: '20px' }}>
          <Routes>
            <Route path="/comments" element={
              <DataTablePage
                title="Комментарии"
                headers={[
                  { field: 'id', title: 'ID' },
                  { field: 'name', title: 'Имя' },
                  { field: 'email', title: 'Email' },
                  { field: 'body', title: 'Текст' }
                ]}
                data={commentsData}
                setData={setCommentsData}
                url="https://jsonplaceholder.typicode.com/comments"
                addFormSchema={commentSchema}
                addFormFields={commentFields}
                onEdit={handleEdit}
                onDelete={handleDelete}
              />
            } />
            <Route path="/posts" element={
              <DataTablePage
                title="Посты"
                headers={[
                  { field: 'id', title: 'ID' },
                  { field: 'title', title: 'Заголовок' },
                  { field: 'body', title: 'Текст' }
                ]}
                data={postsData}
                setData={setPostsData}
                url="https://jsonplaceholder.typicode.com/posts"
                addFormSchema={postSchema}
                addFormFields={postFields}
                onEdit={handleEdit}
                onDelete={handleDelete}
              />
            } />
            <Route path="/albums" element={
              <DataTablePage
                title="Альбомы"
                headers={[
                  { field: 'id', title: 'ID' },
                  { field: 'title', title: 'Название' }
                ]}
                data={albumsData}
                setData={setAlbumsData}
                url="https://jsonplaceholder.typicode.com/albums"
                addFormSchema={albumSchema}
                addFormFields={albumFields}
                onEdit={handleEdit}
                onDelete={handleDelete}
              />
            } />
            <Route path="/todos" element={
            <DataTablePage
              title="Задачи"
              headers={[
                { field: 'id', title: 'ID' },
                { field: 'title', title: 'Название' },
                { field: 'completed', title: 'Выполнено' }
              ]}
              data={todosData}
              setData={setTodosData}
              url="https://jsonplaceholder.typicode.com/todos"
              addFormSchema={todoSchema}
              addFormFields={todoFields}
              onEdit={handleEdit}
              onDelete={handleDelete}
              renderCell={(item, field, rowIndex) => {
                if (field === 'completed') {
                  return (
                    <td 
                      style={{ 
                        cursor: 'pointer',
                        color: item.completed ? 'green' : 'inherit',
                        fontWeight: item.completed ? 'bold' : 'normal'
                      }}
                      onClick={(e) => {
                        e.stopPropagation();
                        const updatedItem = { ...item, completed: !item.completed };
                        handleEdit(rowIndex, 'completed', !item.completed, updatedItem);
                      }}
                    >
                      {item.completed ? '✓ Выполнено' : '✗ Не выполнено'}
                    </td>
                  );
                }
                return <td>{item[field]}</td>;
              }}
              rowStyle={(item) => item.completed ? { backgroundColor: '#e8f5e9' } : {}}
            />
          } />
            <Route path="/users" element={
              <DataTablePage
                title="Пользователи"
                headers={[
                  { field: 'id', title: 'ID' },
                  { field: 'name', title: 'Имя' },
                  { field: 'username', title: 'Логин' },
                  { field: 'email', title: 'Email' },
                  { field: 'phone', title: 'Телефон' },
                  { field: 'website', title: 'Сайт' }
                ]}
                data={usersData}
                setData={setUsersData}
                url="https://jsonplaceholder.typicode.com/users"
                addFormSchema={userSchema}
                addFormFields={userFields}
                onEdit={handleEdit}
                onDelete={handleDelete}
              />
            } />
            <Route path="/" element={<Navigate to="/comments" replace />} />
          </Routes>
        </div>
      </div>
    </Router>
  );
};

const DataTablePage = ({ 
  title, 
  headers, 
  data, 
  setData, 
  url,
  addFormSchema,
  addFormFields,
  onEdit,
  onDelete
}) => {
  const handleEdit = async (rowIndex, field, value, updatedItem) => {
    try {
      await onEdit(url, rowIndex, field, value, updatedItem, setData);
    } catch (err) {
      console.error('Ошибка обновления:', err);
    }
  };

  const handleAdd = async (values, { resetForm }) => {
    try {
      const response = await fetch(url, {
        method: 'POST',
        body: JSON.stringify(values),
        headers: {
          'Content-type': 'application/json; charset=UTF-8',
        },
      });

      const createdItem = await response.json();
      setData(prev => [...prev, createdItem]);
      resetForm();
    } catch (err) {
      console.error('Ошибка добавления:', err);
    }
  };

  const handleDelete = async (indexes) => {
    try {
      await onDelete(url, indexes, data, setData);
    } catch (err) {
      console.error('Ошибка удаления:', err);
    }
  };

  return (
    <div>
      <h1>{title}</h1>
      
      <div style={{ marginBottom: '20px', padding: '20px', border: '1px solid #ddd', borderRadius: '5px' }}>
        <h3>Добавить новую запись</h3>
        <AddForm 
          schema={addFormSchema}
          fields={addFormFields}
          onSubmit={handleAdd}
        />
      </div>
        
      <CommentsApp
      headers={headers}
      data={data}
      onEdit={handleEdit}
      onAdd={() => {}}
      onDelete={handleDelete}
      renderCell={(item, field, rowIndex) => {
        if (field === 'completed') {
          return (
            <div 
              style={{ 
                cursor: 'pointer',
                color: item.completed ? 'green' : 'inherit',
                fontWeight: item.completed ? 'bold' : 'normal'
              }}
              onClick={(e) => {
                e.stopPropagation();
                const updatedItem = { ...item, completed: !item.completed };
                handleEdit(rowIndex, 'completed', !item.completed, updatedItem);
              }}
            >
              {item.completed ? '✓ Выполнено' : '✗ Не выполнено'}
            </div>
          );
        }
        return item[field];
      }}
      rowStyle={(item) => item.completed ? { backgroundColor: '#e8f5e9' } : {}}
    />
    </div>
  );
};

const AddForm = ({ schema, fields, onSubmit }) => {
  return (
    <Formik
      initialValues={fields.reduce((acc, field) => ({ ...acc, [field.name]: '' }), {})}
      validationSchema={schema}
      onSubmit={onSubmit}
    >
      {({ isSubmitting }) => (
        <Form style={{ display: 'flex', flexDirection: 'column', gap: '10px' }}>
          {fields.map(field => (
            <div key={field.name}>
              <label htmlFor={field.name}>{field.label}</label>
              <Field 
                type={field.type || 'text'} 
                name={field.name} 
                id={field.name}
                as={field.as}
              />
              <ErrorMessage name={field.name} component="div" style={{ color: 'red', fontSize: '12px' }} />
            </div>
          ))}
          <button type="submit" disabled={isSubmitting}>
            {isSubmitting ? 'Добавление...' : 'Добавить'}
          </button>
        </Form>
      )}
    </Formik>
  );
};

const navLinkStyle = {
  padding: '10px',
  margin: '5px 0',
  color: '#333',
  textDecoration: 'none',
  borderRadius: '4px',
  transition: 'background-color 0.3s',
  ':hover': {
    backgroundColor: '#ddd',
  }
};

const commentSchema = Yup.object().shape({
  name: Yup.string().required('Обязательное поле'),
  email: Yup.string().email('Некорректный email').required('Обязательное поле'),
  body: Yup.string().required('Обязательное поле')
});

const commentFields = [
  { name: 'name', label: 'Имя' },
  { name: 'email', label: 'Email', type: 'email' },
  { name: 'body', label: 'Текст', as: 'textarea' }
];

const postSchema = Yup.object().shape({
  title: Yup.string().required('Обязательное поле'),
  body: Yup.string().required('Обязательное поле')
});

const postFields = [
  { name: 'title', label: 'Заголовок' },
  { name: 'body', label: 'Текст', as: 'textarea' }
];

const albumSchema = Yup.object().shape({
  title: Yup.string().required('Обязательное поле')
});

const albumFields = [
  { name: 'title', label: 'Название' }
];

const todoSchema = Yup.object().shape({
  title: Yup.string().required('Обязательное поле'),
  completed: Yup.boolean()
});

const todoFields = [
  { name: 'title', label: 'Название' },
  { name: 'completed', label: 'Выполнено', type: 'checkbox' }
];

const userSchema = Yup.object().shape({
  name: Yup.string().required('Обязательное поле'),
  username: Yup.string().required('Обязательное поле'),
  email: Yup.string().email('Некорректный email').required('Обязательное поле'),
  phone: Yup.string(),
  website: Yup.string().url('Некорректный URL')
});

const userFields = [
  { name: 'name', label: 'Имя' },
  { name: 'username', label: 'Логин' },
  { name: 'email', label: 'Email', type: 'email' },
  { name: 'phone', label: 'Телефон' },
  { name: 'website', label: 'Сайт' }
];

export default App;