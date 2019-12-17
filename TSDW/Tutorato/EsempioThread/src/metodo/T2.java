package metodo;
import java.util.Random;

public class T2 extends Thread{
	Shared n;
	
	T2(Shared n){
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

			if(n.updateAndCheck(80))
				break;
		}
		System.out.println("\t\t\t\tT2:" + "TERMINATED");
	}
	
}
