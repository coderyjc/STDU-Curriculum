/**
 * @Author Jingcun Yan
 * @Date 12:32 2020/11/15
 * @Description
 */

package Domain;

import java.util.Objects;

/**
 * @author Jingcun Yan
 */
public class User {
    /**
     * 用户名
     * varchar 40
     */
    private String userName;

    /**
     * 用户性别
     * int 1
     */
    private Integer userSex;

    /**
     *  用户ID
     *  varchar 20
     */
    private String userId;

    /**
     * 用户的密码
     * varchar 255
     */
    private String userPwd;

    /**
     * 用户的类型
     * int 1
     */
    private Integer userType;

    /**
     * 用户的电话
     * varchar 20
     */
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
        if (this == o) {
            return true;
        }
        if (o == null || getClass() != o.getClass()) {
            return false;
        }

        User user = (User) o;

        return Objects.equals(userId, user.userId);
    }

    @Override
    public String toString() {
        return "User{" +
                "userName='" + userName + '\'' +
                ", userSex=" + userSex +
                ", userId='" + userId + '\'' +
                ", userPwd='" + userPwd + '\'' +
                ", userType=" + userType +
                ", userTel='" + userTel + '\'' +
                '}';
    }

    @Override
    public int hashCode() {
        return userId != null ? userId.hashCode() : 0;
    }
}
