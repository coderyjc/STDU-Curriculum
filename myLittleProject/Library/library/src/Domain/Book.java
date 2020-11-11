package Domain;

import java.util.Objects;

public class Book {
    private String bookISBN; // int 10
    private String bookName; // varchar 20
    private Double bookPrice; // double 4, 2
    private String author; // int 10
    private int stock; // int 2
    private String description; // varchar 200
    private int lent; // int  2

    public Book(){
    }

    public Book(String name){
        this.bookName = name;
    }

    public Book(String bookName, String bookISBN, Double bookPrice, String author, int stock, String description) {
        this.bookName = bookName;
        this.bookISBN = bookISBN;
        this.bookPrice = bookPrice;
        this.author = author;
        this.stock = stock;
        this.description = description;
    }

    public String getBookName() {
        return bookName;
    }

    public void setBookName(String bookName) {
        this.bookName = bookName;
    }

    public String getBookISBN() {
        return bookISBN;
    }

    public void setBookISBN(String bookISBN) {
        this.bookISBN = bookISBN;
    }

    public Double getBookPrice() {
        return bookPrice;
    }

    public void setBookPrice(Double bookPrice) {
        this.bookPrice = bookPrice;
    }

    public String getAuthor() {
        return author;
    }

    public void setAuthor(String author) {
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

        return Objects.equals(bookISBN, book.bookISBN);
    }

    public int getLent() {
        return lent;
    }

    public void setLent(int lent) {
        this.lent = lent;
    }

    @Override
    public int hashCode() {
        return bookISBN != null ? bookISBN.hashCode() : 0;
    }
}
