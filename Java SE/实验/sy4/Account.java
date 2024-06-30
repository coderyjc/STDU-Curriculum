class Account{
    private String account;
    private String name;
    private Date openDate;
    private String id;
    private double balance;

    public Account(){}

    public Account(String account, String name, Date openDate, String id, double balance) {
        this.account = account;
        this.name = name;
        this.openDate = openDate;
        this.id = id;
        this.balance = balance;
    }

    public String getAccount() {return account;}

    public void setAccount(String account) {this.account = account;}

    public String getName() {return name;}

    public void setName(String name) {this.name = name;}

    public Date getOpenDate() {return openDate;}

    public void setOpenDate(Date openDate) {this.openDate = openDate;}

    public String getId() {return id;}

    public void setId(String id) {this.id = id;}

    public double getBalance() {return balance;}

    public void setBalance(double balance) {this.balance = balance;}

    /**
     *  存钱函数
     * @param number 存钱的数量
     * @return number小于1 返回false表示存钱失败，否则返回true，表示存钱成功
     */
    public boolean put(double number){
        if(number < 0) return false;
        this.balance += number;
        return true;
    }

    /**
     *  取钱函数
     * @param number 取钱的金额，
     * @return 如果取钱金额大于余额，则返回false表示取钱失败，否则取钱成功
     */
    public boolean get(double number){
        if(0 > this.balance - number) return  false;
        this.balance -= number;
        return true;
    }

    /**
     *  查看当前的余额有多少，直接输出现在的金额
     */
    public void howMuch(){
        System.out.println("账户现有金额为 " + balance);
    }
}