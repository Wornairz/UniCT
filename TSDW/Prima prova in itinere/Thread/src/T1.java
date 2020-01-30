import java.util.Random;

public class T1 extends Thread {
	private Shared x;
	private int m;
	private Random r;
	
	public T1(Shared shared) {
		super("T1");
		this.x = shared;
		r = new Random();
	}
	
	@Override
	public void run() {
		while(true) {
			try {
				System.out.println("T1 aspetta 100ms");
				sleep(100);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}			
			m = r.nextInt(11);
			synchronized (x) {
				System.out.println("Da indovinare: " + x.x + "\tRisposta data: " + m);
				if(x.x==-1)
					break;
				
				if(m==x.x) {
					System.out.println("RISPOSTA CORRETTA");
					x.x = -1;
					break;
				}
				else if(Math.abs(m-x.x)>5) {
					System.out.println("risposta MOLTO sbagliata");
					try {
						x.wait();
					} catch (InterruptedException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
				}
				else
					System.out.println("risposta sbagliata");
			}			
		}
		System.out.println("----T1 ha finito----");
	}
}
