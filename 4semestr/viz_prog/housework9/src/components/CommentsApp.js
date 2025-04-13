import React, { useState } from 'react';

const CommentsApp = ({
  headers = [],
  data = [],
  onEdit = async () => {},
  onAdd = () => {},
  onDelete = () => {},
  renderHeader = (header, index) => <th key={index}>{header.title || header}</th>,
  renderCell = (item, field, index) => <td key={index}>{item[field]}</td>,
  rowStyle = () => ({})
}) => {
  const derivedHeaders = headers.length > 0 
    ? headers 
    : data.length > 0 
      ? Object.keys(data[0]).map(key => ({ field: key, title: key })) 
      : [];

  const [selectedRows, setSelectedRows] = useState(new Set());
  const [loadingRows, setLoadingRows] = useState(new Set());
  const [error, setError] = useState(null);
  const [editingCell, setEditingCell] = useState(null);
  const [editValue, setEditValue] = useState('');

  const handleRowSelect = (index, event) => {
    event.stopPropagation();
    const isCtrlPressed = event.ctrlKey || event.metaKey;

    setSelectedRows(prevSelected => {
      const newSelected = new Set(prevSelected);
      
      if (isCtrlPressed) {
        if (newSelected.has(index)) {
          newSelected.delete(index);
        } else {
          newSelected.add(index);
        }
      } else {
        if (newSelected.has(index)) {
          newSelected.clear();
        } else {
          newSelected.clear();
          newSelected.add(index);
        }
      }
      
      return newSelected;
    });
  };

  const startEditing = (rowIndex, field, value) => {
    setEditingCell({ rowIndex, field });
    setEditValue(value);
  };

  const cancelEditing = () => {
    setEditingCell(null);
    setEditValue('');
  };

  const saveEditing = async () => {
    if (!editingCell) return;
    
    const { rowIndex, field } = editingCell;
    
    try {
      setLoadingRows(prev => new Set(prev).add(rowIndex));
      setError(null);

      const updatedItem = {
        ...data[rowIndex],
        [field]: editValue
      };

      await onEdit(rowIndex, field, editValue, updatedItem);
      setEditingCell(null);
    } catch (err) {
      setError(`Ошибка при обновлении: ${err.message}`);
    } finally {
      setLoadingRows(prev => {
        const newSet = new Set(prev);
        newSet.delete(rowIndex);
        return newSet;
      });
    }
  };

  const handleDelete = async () => {
    if (selectedRows.size === 0) return;
    
    try {
      setLoadingRows(selectedRows);
      setError(null);
      await onDelete(Array.from(selectedRows));
      setSelectedRows(new Set());
    } catch (err) {
      setError(`Ошибка при удалении: ${err.message}`);
    } finally {
      setLoadingRows(new Set());
    }
  };

  if (data.length === 0) {
    return (
      <div>
        <div style={{ marginBottom: '10px' }}>
        </div>
        <div>Нет данных для отображения</div>
      </div>
    );
  }

  return (
    <div>
      {error && <div style={{ color: 'red', marginBottom: '10px' }}>{error}</div>}
      
      <div style={{ marginBottom: '10px' }}>
        <button 
          onClick={handleDelete}
          disabled={selectedRows.size === 0 || loadingRows.size > 0}
          style={{ padding: '5px 10px', background: '#f44336', color: 'white', border: 'none' }}
        >
          {loadingRows.size > 0 ? 'Удаление...' : `Удалить выбранные (${selectedRows.size})`}
        </button>
      </div>

      <table style={{ 
        borderCollapse: 'collapse', 
        width: '100%', 
        margin: '20px 0',
        border: '1px solid #ddd'
      }}>
        <thead>
          <tr>
            <th style={{ width: '30px', background: '#f0f0f0' }}></th>
            {derivedHeaders.map((header, index) => 
              renderHeader(header, index)
            )}
          </tr>
        </thead>
        <tbody>
          {data.map((item, rowIndex) => (
            <tr 
              key={rowIndex}
              style={{ 
                backgroundColor: selectedRows.has(rowIndex) ? '#e6f7ff' : 'transparent',
                cursor: 'pointer',
                opacity: loadingRows.has(rowIndex) ? 0.5 : 1,
                ...rowStyle(item)
              }}
              onClick={(e) => !loadingRows.has(rowIndex) && handleRowSelect(rowIndex, e)}
            >
              <td 
                style={{ 
                  border: '1px solid #ddd',
                  background: selectedRows.has(rowIndex) ? '#e6f7ff' : '#f9f9f9'
                }}
              >
                {loadingRows.has(rowIndex) ? '⌛' : ' '}
              </td>
              {derivedHeaders.map((header, cellIndex) => (
              <td 
                key={cellIndex} 
                style={{ border: '1px solid #ddd', padding: '8px' }}
                onDoubleClick={(e) => {
                  e.stopPropagation();
                  if (!loadingRows.has(rowIndex)) {
                    startEditing(rowIndex, header.field, item[header.field]);
                  }
                }}
              >
                {editingCell?.rowIndex === rowIndex && editingCell?.field === header.field ? (
                  <div style={{ display: 'flex', gap: '5px' }}>
                    <input
                      type="text"
                      value={editValue}
                      onChange={(e) => setEditValue(e.target.value)}
                      autoFocus
                      style={{ flex: 1 }}
                    />
                    <button onClick={saveEditing}>✓</button>
                    <button onClick={cancelEditing}>✕</button>
                  </div>
                ) : (
                  <div style={{ width: '100%' }}>
                    {renderCell(item, header.field, rowIndex)}
                  </div>
                )}
              </td>
            ))}
            </tr>
          ))}
        </tbody>
      </table>
    </div>
  );
};

export default CommentsApp;