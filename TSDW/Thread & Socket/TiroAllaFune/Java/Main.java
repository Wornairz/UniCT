public class Main {

    public static void main(String[] args) {
        Giocatore tp0 = new Giocatore("tp0");
        Giocatore tp1 = new Giocatore("\t\t\t\t\t\t\t\t\t\ttp1");
        tp0.setRivale(tp1); tp1.setRivale(tp0 );
        tp0.start(); tp1.start();
        try {
            tp0.join();
            tp1.join();
        } catch (InterruptedException e){
            e.printStackTrace();
        }

        if(Giocatore.vittorieTP0 > Giocatore.vittorieTP1)
            System.out.println("Il vincitore è TP0");
        else
            System.out.println("Il vincitore è TP1");

        System.out.println("Il risultato finale è di " + Giocatore.vittorieTP0 + " - " + Giocatore.vittorieTP1);
    }
}
