package metodo;
import java.util.Random;

public class Shared {
	Integer n = 100;
	Random r = new Random();

	public synchronized boolean updateAndCheck(int bound) {
		int nrand = r.nextInt(10);
		if(bound == 80)
			nrand *= -1;
		n += nrand;
		
		if(bound == 80)
			System.out.print("\t\t\t\tT2:");
		else if(bound == 150)
			System.out.print("T1:");
		System.out.println(n);
		
		return (bound == 80 && n<bound) || (bound == 150 && n>bound);
	}
}
