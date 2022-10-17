SELECT MAX(v4.book.pages) FROM v4.book;
SELECT MIN(v4.info.pages) FROM v4.info WHERE v4.info.bookgenre = 'comedy';
SELECT AVG(v4.info.pages) FROM v4.info WHERE v4.info.bookgenre = 'science fiction';
SELECT COUNT(v4.info.bookName) FROM v4.info WHERE v4.info.publHouse = 'Siberia';
SELECT SUM(v4.info.price) FROM v4.info WHERE v4.info.cityname = 'Moscow';