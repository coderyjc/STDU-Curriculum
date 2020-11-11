package Domain;

import java.util.Objects;

public class Book {
    private Integer bookId; // int 10
    private String bookName; // varchar 20
    private Double bookPrice; // double 4, 2
    private int author; // int 10
    private int stock; // int 2
    private String description; // varchar 200
    private int lent; // int  2

    public Book(String bookName, int bookId, Double bookPrice, int author, int stock, String description, int lent) {
        this.bookName = bookName;
        this.bookId = bookId;
        this.bookPrice = bookPrice;
        this.author = author;
        this.stock = stock;
        this.description = description;
        this.lent = lent;
    }

    public String getBookName() {
        return bookName;
    }

    public void setBookName(String bookName) {
        this.bookName = bookName;
    }

    public int getBookId() {
        return bookId;
    }

    public void setBookId(int bookId) {
        this.bookId = bookId;
    }

    public Double getBookPrice() {
        return bookPrice;
    }

    public void setBookPrice(Double bookPrice) {
        this.bookPrice = bookPrice;
    }

    public int getAuthor() {
        return author;
    }

    public void setAuthor(int author) {
        this.author = author;
    }

    public int getStock() {
        return stock;
    }

    public void setStock(int stock) {
        this.stock = stock;
    }

    public String getDescription() {
        return description;
    }

    public void setDescription(String description) {
        this.description = description;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        Book book = (Book) o;

        return Objects.equals(bookId, book.bookId);
    }

    public int getLent() {
        return lent;
    }

    public void setLent(int lent) {
        this.lent = lent;
    }

    @Override
    public int hashCode() {
        return bookId != null ? bookId.hashCode() : 0;
    }
}
