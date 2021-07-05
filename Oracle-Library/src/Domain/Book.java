/**
 * @Author Jingcun Yan
 * @Date 07:32 2020/11/16
 * @Description
 */

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
     * 书籍现在的状态，是借出去了还是在库中
     * 1 表示借出去了
     * 0 表示还在库中
     */
    private int status;

    /**
     * 书籍的类型
     * 在数据库的book表中是int(3), 前端有详细的东西
     */
    private String type;

    public Book(){}

    public Book(String isbn){
        this.bookISBN = isbn;
    }

    public Book(String bookISBN, String bookName, Double bookPrice, String author, int status, String type) {
        this.bookISBN = bookISBN;
        this.bookName = bookName;
        this.bookPrice = bookPrice;
        this.author = author;
        this.status = status;
        this.type = type;
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

    public void setStatus(int status) {
        this.status = status;
    }

    public int getStatus(){
        return this.status;
    }

    public void setType(String type) {
        this.type = type;
    }

    public String getType() {
        return type;
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

    @Override
    public String toString() {
        return "Book{" +
                "bookISBN='" + bookISBN + '\'' +
                ", bookName='" + bookName + '\'' +
                ", bookPrice=" + bookPrice +
                ", author='" + author + '\'' +
                ", status=" + status +
                ", type='" + type + '\'' +
                '}';
    }

    @Override
    public int hashCode() {
        return bookISBN != null ? bookISBN.hashCode() : 0;
    }
}
