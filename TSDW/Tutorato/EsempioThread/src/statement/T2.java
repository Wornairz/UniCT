package statement;
import java.util.Random;

public class T2 extends Thread{
	Integer n;
	
	T2(Integer n){
		this.n = n;
	}

	@Override
	public void run() {
		Random r = new Random();
		for(int i=0; i<1000; i++) {
			try {
				sleep(300);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			int nrand = r.nextInt(10);
			
			synchronized (n) {
				n -= nrand;
				System.out.println("\t\t\t\tT2:" + n);
				if(n<80)
					break;
			}
		}
		System.out.println("\t\t\t\tT2:" + "TERMINATED");
	}
	
}
