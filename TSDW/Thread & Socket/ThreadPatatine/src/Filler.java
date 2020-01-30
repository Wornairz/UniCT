
import java.util.logging.Level;
import java.util.logging.Logger;

public class Filler implements Runnable{
    Patatine pacco;
    int numeroVolteRiempite;
    
    Filler(Patatine p){
        this.pacco = p;
        numeroVolteRiempite = 0;
    }
    @Override
    public void run() {
        try {
            while(numeroVolteRiempite < 4){//il pacco non viene riempito più dopo la 4° volta
                Thread.sleep(2000);
                if(pacco.rifornimentoPatatine())
                    numeroVolteRiempite++;
            }
            
        } catch (InterruptedException ex) {
            Logger.getLogger(Filler.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    
}
