package Domain;

import java.util.Objects;

public class Book {
    /**
     * 书籍的ISBN
     * 建表方式 varchar 20
     */
    private String bookISBN;

    /**
     * 书名字
     * 建表方式 varchar 255
     */
    private String bookName;

    /**
     * 书籍的价格
     * varchar 10, 2
     */
    private Double bookPrice;

    /**
     * 书籍的作者（考虑使用表连接，目前还没有实现）
     * varchar 255
     */
    private String author;

    /**
     * 书籍目前的库存
     * int 10
     */
    private int stock;

    /**
     * 书籍的简介
     * varchar 200
     */
    private String description;

    /**
     * 已经借出去的书籍的数量
     * int 10
     */
    private int lent;

    public Book(){}

    public Book(String isbn){
        this.bookISBN = isbn;
    }

    public Book(String bookName, String bookISBN, Double bookPrice, String author, int stock, String description) {
        this.bookName = bookName;
        this.bookISBN = bookISBN;
        this.bookPrice = bookPrice;
        this.author = author;
        this.stock = stock;
        this.description = description;
    }

    public Book(String bookISBN, String bookName, Double bookPrice, String author, int stock, String description, int lent) {
        this.bookISBN = bookISBN;
        this.bookName = bookName;
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
        if (this == o) {
            return true;
        }
        if (o == null || getClass() != o.getClass()) {
            return false;
        }

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
