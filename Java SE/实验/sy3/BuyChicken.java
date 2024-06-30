public class BuyChicken{
    public static void main(String[] args) {

        int cock = 0;
        int hen = 0;
        int chicken = 0;

        for(cock = 0; cock <= 20; cock++){
            for(hen = 0; hen <= 33; hen++){
                for(chicken = 0; chicken <= 300; chicken += 3){
                    if(chicken/3 + hen*3 + cock*5 == 100 && chicken + cock + hen ==100){
                        System.out.println("cock = " + cock +
                                " hen = " + hen +
                                " chicken = " + chicken);
                    }
                }
            }
        }
    }
}