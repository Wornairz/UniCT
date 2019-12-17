
public class T1 implements Runnable{

    Patatine pacco;
    int numeroPatatineMangiate;
    
    T1(Patatine p){
        this.pacco = p;
        numeroPatatineMangiate = 0;
    }
    
    @Override
    public void run() {
        while(true){
            try {
                Thread.sleep(1000);
                int q = pacco.getPatatine();
                numeroPatatineMangiate += q;
                System.out.println(Thread.currentThread().getName() + " prende " + q + " patatine");
            } catch (InterruptedException ex) {
               ex.printStackTrace();
            }
        }
        
    }
    
}
