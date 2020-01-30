
public class main {
    public static void main(String[] args) {
        Patatine pacco = new Patatine(400);
        new Thread(new T1(pacco), "Dani").start();
        new Thread(new T1(pacco), "Ale").start();
        new Thread(new T1(pacco), "Fox").start();
        new Thread(new T1(pacco), "Saro").start();
        new Thread(new T1(pacco), "Simo").start();
        new Thread(new T1(pacco), "Peppe").start();
        new Thread(new Filler(pacco), "Mago Merlino").start();
    }
}
