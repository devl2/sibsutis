import React, { useEffect, useState } from 'react';
import BookCard from './BookCard';
import SearchAndSort from './SearchAndSort';

const App = () => {
  const [books, setBooks] = useState([]);
  const [filteredBooks, setFilteredBooks] = useState([]);
  const [searchTerm, setSearchTerm] = useState('');
  const [sortBy, setSortBy] = useState('title');
  const [sortOrder, setSortOrder] = useState('asc');

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
        setFilteredBooks(booksWithCovers);
      } catch (error) {
        console.error('Error fetching books:', error);
      }
    };

    fetchBooks();
  }, [sortBy, setSortBy, sortOrder, setSortOrder]);

  useEffect(() => {
    const filtered = books.filter(book =>
      book.title.toLowerCase().includes(searchTerm.toLowerCase()) ||
      book.authors.join(', ').toLowerCase().includes(searchTerm.toLowerCase())
    );
    setFilteredBooks(filtered);
  }, [searchTerm, books]);

  const handleSort = (sortBy, sortOrder) => {
    const sortedBooks = [...filteredBooks].sort((a, b) => {
      if (sortBy === 'title') {
        return sortOrder === 'asc'
          ? a.title.localeCompare(b.title)
          : b.title.localeCompare(a.title);
      } else if (sortBy === 'authors') {
        return sortOrder === 'asc'
          ? a.authors.join(', ').localeCompare(b.authors.join(', '))
          : b.authors.join(', ').localeCompare(a.authors.join(', '));
      }
      return 0;
    });
    setFilteredBooks(sortedBooks);
  };

  return (
    <div style={styles.app}>
      <SearchAndSort
        onSearch={setSearchTerm}
        onSort={handleSort}
      />
      {filteredBooks.map((book) => (
        <BookCard
          key={book.id}
          title={book.title}
          authors={book.authors}
          coverImage={book.coverImage}
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