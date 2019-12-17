public class Patatine {
    
    int numeroPatatine;
    boolean refillTerminati;
    
    Patatine(int n){
        this.numeroPatatine = n;
        refillTerminati = false;
    }
    
    public synchronized int getPatatine() throws InterruptedException{
        System.out.println("Numero patatine: " + numeroPatatine);
        if(numeroPatatine <= 0)
            wait();
        int quantità = (int) (Math.random()*10)+1;
        if(quantità > numeroPatatine)
            quantità = numeroPatatine;
        numeroPatatine -= quantità;
        return quantità;
    }
    
    public synchronized boolean rifornimentoPatatine(){
        if(numeroPatatine <= 0){
            System.out.println("Riempio il pacco di patatine");
            numeroPatatine = (int) (Math.random()*200)+1;
            notifyAll();
            return true;
        }   
        return false;
    }
 /*   
    public synchronized boolean getRefillTerminti(){
        return refillTerminati;
    }
 
    public synchronized setRefillTerminti(boolean val){
        this.refillTerminati = val;
    }
 */
}
