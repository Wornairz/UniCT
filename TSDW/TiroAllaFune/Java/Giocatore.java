import java.util.Random;

public class Giocatore extends Thread{
    private static int posizione = 0;
    public static int vittorieTP0 = 0;
    public static int vittorieTP1 = 0;
    private Giocatore rivale;

    public Giocatore(String nome){
        super(nome);
    }

    private synchronized void tira(int forza) throws InterruptedException {
        Giocatore.posizione += forza*(getName().contains("tp0") ? -1 : 1);
        System.out.println(getName() + ": posizione ora -> " + Giocatore.posizione);
        if(Giocatore.posizione <= -10 && getName().equals("tp0")) {
            System.out.println(getName() + ": ho vinto! Attendo...");
            wait();
        }
        else if(Giocatore.posizione >= 10 && getName().contains("tp1")) {
            System.out.println(getName() + ": ho vinto! Attendo...");
            wait();
        }
    }

    private synchronized boolean checkVictory(){
        if(Giocatore.posizione>=10 && getName().contains("tp0")){
            System.out.println(getName() + ": ho perso!");
            vittorieTP1++;
            posizione = 0;
            synchronized (rivale) {
                rivale.notifyAll();
            }
            return true;
        }
        else if(Giocatore.posizione<=-10 && getName().contains("tp1")){
            System.out.println(getName() + ": ho perso!");
            vittorieTP0++;
            posizione = 0;
            synchronized (rivale) {
                rivale.notifyAll();
            }
            return true;
        }
        return false;
    }

    private synchronized boolean endGame(){
        if(Giocatore.vittorieTP1 == 10 || Giocatore.vittorieTP0 == 10) {
            System.out.println("Gioco terminato!");
            return true;
        }
        return false;
    }

    public void setRivale(Giocatore rivale){
        this.rivale = rivale;
    }

    @Override
    public void run() {
        Random random = new Random();
        int recupero, forza;
        while(true){

            if(checkVictory())
                continue;

            if(endGame())
                break;

            forza = random.nextInt(6);
            System.out.println(getName() + ": tiro la fune con forza " + forza);
            try {
                tira(forza);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }


            recupero = random.nextInt(4);
            System.out.println(getName() + ": attendo " + recupero + " secondi per recuperare le forze");
            try {
                Thread.sleep(recupero*1000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}
