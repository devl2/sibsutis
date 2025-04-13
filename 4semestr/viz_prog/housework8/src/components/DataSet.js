import React, { useState } from 'react';

const DataSet = ({
  headers = [],
  data = [],
  renderHeader = (header, index) => <th key={index}>{header.title || header}</th>,
  renderCell = (item, field, index) => <td key={index}>{item[field]}</td>,
}) => {
  const derivedHeaders = headers.length > 0 
    ? headers 
    : data.length > 0 
      ? Object.keys(data[0]).map(key => ({ field: key, title: key })) 
      : [];

  const [selectedRows, setSelectedRows] = useState(new Set());

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

  if (data.length === 0) {
    return <div>Нет данных для отображения</div>;
  }

  return (
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
              cursor: 'pointer'
            }}
            onClick={(e) => handleRowSelect(rowIndex, e)}
          >
            <td 
              style={{ 
                border: '1px solid #ddd',
                background: selectedRows.has(rowIndex) ? '#e6f7ff' : '#f9f9f9'
              }}
            >
              &nbsp;
            </td>
            {derivedHeaders.map((header, cellIndex) => (
              <td 
                key={cellIndex} 
                style={{ border: '1px solid #ddd', padding: '8px' }}
              >
                {renderCell(item, header.field || header, cellIndex)}
              </td>
            ))}
          </tr>
        ))}
      </tbody>
    </table>
  );
};

export default DataSet;