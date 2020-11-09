package Domain;

import java.util.Objects;

public class User {
    private String userName;
    private int userSex;
    private String userId;
    private String userPwd;
    private int userType;
    private String userTel;

    public User() {}

    public User(String userId){
        this.userId = userId;
    }

    public User(String userId, String passWord){
        this.userId = userId;
        this.userPwd = passWord;
    }

    public User(String userName, int userSex, String userId, String userPwd, int userType, String userTel) {
        this.userName = userName;
        this.userSex = userSex;
        this.userId = userId;
        this.userPwd = userPwd;
        this.userType = userType;
        this.userTel = userTel;
    }

    public String getUserName() {
        return userName;
    }

    public void setUserName(String userName) {
        this.userName = userName;
    }

    public int getUserSex() {
        return userSex;
    }

    public void setUserSex(int userSex) {
        this.userSex = userSex;
    }

    public String getUserId() {
        return userId;
    }

    public void setUserId(String userId) {
        this.userId = userId;
    }

    public String getUserPwd() {
        return userPwd;
    }

    public void setUserPwd(String userPwd) {
        this.userPwd = userPwd;
    }

    public int getUserType() {
        return userType;
    }

    public void setUserType(int userType) {
        this.userType = userType;
    }

    public String getUserTel() {
        return userTel;
    }

    public void setUserTel(String userTel) {
        this.userTel = userTel;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        User user = (User) o;

        return Objects.equals(userId, user.userId);
    }

    @Override
    public int hashCode() {
        return userId != null ? userId.hashCode() : 0;
    }
}
