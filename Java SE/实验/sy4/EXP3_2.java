class EXP3_2 {

    public static void main(String[] args) {

        EXP3_2 e = new EXP3_1("王大力", 70, 30);
        e.changeSpeed(90); // 将车速改变为 90
        e.stop(); // 停车
    }


    private String ownerName;
    private float curSpeed;
    private float curDirInDegerr;

    public EXP3_1(String ownerName) {
        this.ownerName = ownerName;
    }

    public EXP3_1(String ownerName, float curSpeed, float curDirInDegerr) {
        this.ownerName = ownerName;
        this.curSpeed = curSpeed;
        this.curDirInDegerr = curDirInDegerr;
    }

    public String getOwnerName() {
        return ownerName;
    }

    public float getCurSpeed() {
        return curSpeed;
    }

    public float getCurDirInDegerr() {
        return curDirInDegerr;
    }

    public void changeSpeed(float curSpeed){
        this.curSpeed = curSpeed;
    }

    public void stop() {
        this.curSpeed = 0;
    }
}

