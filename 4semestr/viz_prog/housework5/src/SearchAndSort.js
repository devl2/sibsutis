import React, { useState } from 'react';

const SearchAndSort = ({ onSearch, onSort }) => {
  const [searchTerm, setSearchTerm] = useState('');
  const [sortBy, setSortBy] = useState('title');
  const [sortOrder, setSortOrder] = useState('asc');

  const handleSearchChange = (e) => {
    const term = e.target.value;
    setSearchTerm(term);
    onSearch(term);
  };

  const handleSortChange = (e) => {
    const { name, value } = e.target;
    if (name === 'sortBy') {
      setSortBy(value);
      onSort(value, sortOrder);
    } else if (name === 'sortOrder') {
      setSortOrder(value);
      onSort(sortBy, value);
    }
  };

  return (
    <div style={styles.container}>
      <input
        type="text"
        placeholder="Поиск по названию или автору"
        value={searchTerm}
        onChange={handleSearchChange}
        style={styles.searchInput}
      />
      <div style={styles.sortContainer}>
        <label>
          Сортировать по:
          <select name="sortBy" value={sortBy} onChange={handleSortChange} style={styles.select}>
            <option value="title">Название</option>
            <option value="authors">Автор</option>
          </select>
        </label>
        <label>
          Порядок сортировки:
          <select name="sortOrder" value={sortOrder} onChange={handleSortChange} style={styles.select}>
            <option value="asc">По возрастанию</option>
            <option value="desc">По убыванию</option>
          </select>
        </label>
      </div>
    </div>
  );
};

const styles = {
  container: {
    marginBottom: '20px',
  },
  searchInput: {
    width: '100%',
    padding: '10px',
    fontSize: '16px',
    borderRadius: '4px',
    border: '1px solid #ddd',
    marginBottom: '10px',
  },
  sortContainer: {
    display: 'flex',
    justifyContent: 'space-between',
  },
  select: {
    marginLeft: '10px',
    padding: '5px',
    fontSize: '14px',
  },
};

export default SearchAndSort;