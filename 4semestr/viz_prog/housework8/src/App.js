import React, { useState, useEffect } from 'react';
import CommentsApp from './components/CommentsApp';
import DataSet from './components/DataSet';

const App = () => {
  const [data, setData] = useState([]);
  const [loading, setLoading] = useState(true);

  const products = [
    { productId: 'P100', name: 'Ноутбук', price: 1200 },
    { productId: 'P101', name: 'Смартфон', price: 800 },
    { productId: 'P102', name: 'Камера', price: 600 },
    { productId: 'P103', name: 'Пылесос', price: 300 },
    { productId: 'P104', name: 'Кофемашина', price: 550 },
    { productId: 'P105', name: 'Холодильник', price: 900 },
  ];

  const productHeaders = [
    { field: 'productId', title: 'Артикул' },
    { field: 'name', title: 'Наименование' },
    { field: 'price', title: 'Цена ($)' }
  ];

  // Загрузка данных
  useEffect(() => {
    const fetchData = async () => {
      try {
        const response = await fetch('https://jsonplaceholder.typicode.com/comments?');
        const json = await response.json();
        setData(json.slice(0, 10));
      } catch (err) {
        console.error('Ошибка загрузки:', err);
      } finally {
        setLoading(false);
      }
    };

    fetchData();
  }, []);

  const handleEdit = async (rowIndex, field, value, updatedItem) => {
    try {
      const response = await fetch(
        `https://jsonplaceholder.typicode.com/comments/${updatedItem.id}`,
        {
          method: 'PATCH',
          body: JSON.stringify({ [field]: value }),
          headers: {
            'Content-type': 'application/json; charset=UTF-8',
          },
        }
      );

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

  const handleAdd = async () => {
    const newItem = {
      name: '',
      email: '',
      body: '',
      postId: 1
    };

    try {
      const response = await fetch('https://jsonplaceholder.typicode.com/comments', {
        method: 'POST',
        body: JSON.stringify(newItem),
        headers: {
          'Content-type': 'application/json; charset=UTF-8',
        },
      });

      const createdItem = await response.json();
      setData(prev => [...prev, createdItem]);
    } catch (err) {
      console.error('Ошибка добавления:', err);
    }
  };

  const handleDelete = async (indexes) => {
    try {
      const deletePromises = indexes.map(index => 
        fetch(`https://jsonplaceholder.typicode.com/comments/${data[index].id}`, {
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
    <div style={{ padding: '20px' }}>
      {/* <DataSet 
              headers={productHeaders}
              data={products}
              renderCell={(item, field) => {
                if (field === 'price') {
                  return <td style={{ textAlign: 'right' }}>${item[field]}</td>;
                }
                return <td>{item[field]}</td>;
              }}
            /> */}
        <CommentsApp
        headers={[
          { field: 'id', title: 'ID' },
          { field: 'name', title: 'Имя' },
          { field: 'email', title: 'Email' },
          { field: 'body', title: 'Текст' }
        ]}
        data={data}
        onEdit={handleEdit}
        onAdd={handleAdd}
        onDelete={handleDelete}
        />
    </div>
  );
};

export default App;