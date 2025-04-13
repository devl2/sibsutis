import React from 'react';

const BookCard = ({ title, authors, coverImage }) => {
  return (
    <div style={styles.card}>
      {coverImage && <img src={coverImage} alt={title} style={styles.cover} />}
      <h2 style={styles.title}>{title}</h2>
      <p style={styles.authors}>{authors.join(', ')}</p>
      <button style={styles.buybutton}> Купить </button>
    </div>
  );
};

const styles = {
  card: {
    width: '200px',
    margin: '10px',
    textAlign: 'center',
    border: '1px solid #ddd',
    borderRadius: '8px',
    padding: '10px',
    boxShadow: '0 2px 4px rgba(0, 0, 0, 0.1)',
  },
  cover: {
    width: '100%',
    height: 'auto',
    borderRadius: '4px',
  },
  title: {
    fontSize: '22px',
    margin: '10px 0',
  },
  authors: {
    fontSize: '14px',
    color: '#555',
  },
  buybutton: {
    background: 'linear-gradient(45deg,rgb(9, 137, 241),rgb(9, 137, 241))',
    border: 'none',
    borderRadius: '3px',
    color: 'white',
    padding: '10px 50px',
    fontSize: '16px',
    fontWeight: 'bold',
    cursor: 'pointer',
    boxShadow: '0px 4px 6px rgba(0, 0, 0, 0.2)',
    transition: 'background 0.3s ease, transform 0.2s ease',
  }
};

export default BookCard;