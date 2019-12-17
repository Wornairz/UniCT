package statement;
import java.util.Random;

public class T1 extends Thread{
	Integer n;
	
	T1(Integer n){
		this.n = n;
	}

	@Override
	public void run() {
		Random r = new Random();
		for(int i=0; i<1000; i++) {
			try {
				sleep(100);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			int nrand = r.nextInt(10);
			
			synchronized (n) {
				n += nrand;
				System.out.println("T1:" + n);
				if(n>150)
					break;
			}
		}
		System.out.println("T1:" + "TERMINATED");
	}
	
}

