import React, { useEffect, useState } from 'react';
import BookCard from './BookCard';

const App = () => {
  const [books, setBooks] = useState([]);

  useEffect(() => {
    const fetchBooks = async () => {
      try {
        const response = await fetch('https://fakeapi.extendsclass.com/books');
        const data = await response.json();

        const booksWithCovers = await Promise.all(
          data.map(async (book) => {
            const googleBooksResponse = await fetch(
              `https://www.googleapis.com/books/v1/volumes?q=isbn:${book.isbn}`
            );
            const googleBooksData = await googleBooksResponse.json();
            const coverImage = googleBooksData.items?.[0]?.volumeInfo?.imageLinks?.thumbnail || null;
            return { ...book, coverImage };
          })
        );

        setBooks(booksWithCovers);
      } catch (error) {
        console.error('Error fetching books:', error);
      }
    };

    fetchBooks();
  }, []);

  return (
    <div style={styles.app}>
      {books.map((book) => (
        <BookCard
          key={book.id}
          title={book.title}
          authors={book.authors}
          coverImage={book.coverImage}
          buy={book.buyButton}
        />
      ))}
    </div>
  );
};

const styles = {
  app: {
    display: 'flex',
    flexWrap: 'wrap',
    justifyContent: 'center',
    padding: '20px',
  },
};

export default App;