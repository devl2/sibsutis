import React, { useState, useEffect } from 'react';
import { Tabs, Tab, Box } from '@mui/material';
import CommentsApp from './components/CommentsApp';
import LogsViewer from './components/LogsViewer';

const API_BASE_URL = 'http://localhost:5065';

const App = () => {
  const [tabValue, setTabValue] = useState(0);

  const handleTabChange = (event, newValue) => {
    setTabValue(newValue);
  };

  return (
    <div style={{ padding: '20px' }}>
      <Box sx={{ borderBottom: 1, borderColor: 'divider' }}>
        <Tabs value={tabValue} onChange={handleTabChange}>
          <Tab label="Comments" />
          <Tab label="Logs" />
        </Tabs>
      </Box>
      <Box sx={{ pt: 3 }}>
        {tabValue === 0 && <CommentsAppWrapper />}
        {tabValue === 1 && <LogsViewer />}
      </Box>
    </div>
  );
};

const CommentsAppWrapper = () => {
  const [data, setData] = useState([]);
  const [loading, setLoading] = useState(true);

  useEffect(() => {
    const fetchData = async () => {
      try {
        const response = await fetch(`${API_BASE_URL}/comments`);
        if (!response.ok) throw new Error('Server error');
        const json = await response.json();
        setData(json);
      } catch (err) {
        console.error('Ошибка загрузки:', err);
        setData([]);
      } finally {
        setLoading(false);
      }
    };

    fetchData();
  }, []);

  const handleEdit = async (rowIndex, field, value, updatedItem) => {
    try {
      const response = await fetch(
        `${API_BASE_URL}/comments/${updatedItem.id}`,
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
      const response = await fetch(`${API_BASE_URL}/comments`, {
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
        fetch(`${API_BASE_URL}/comments/${data[index].id}`, {
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
  );
};

export default App;