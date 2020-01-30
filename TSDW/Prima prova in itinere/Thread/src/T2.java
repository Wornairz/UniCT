import java.util.Random;

public class T2 extends Thread {
	private Shared x;
	private int m;
	private Random r;
	
	public T2(Shared shared) {
		super("T2");
		this.x = shared;
		r = new Random();
	}
	
	@Override
	public void run() {
		while(true) {
			try {
				System.out.println("T2 aspetta 300ms");
				sleep(300);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
			synchronized (x) {
				System.out.println("Sveglio T1...");
				x.notify();
				if(x.x==-1)
					break;
			}
		}
		System.out.println("----T2 ha finito----");
	}
}
