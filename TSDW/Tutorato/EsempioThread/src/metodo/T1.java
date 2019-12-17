package metodo;

public class T1 extends Thread{
	Shared n;
	
	T1(Shared n){
		this.n = n;
	}

	@Override
	public void run() {
		for(int i=0; i<1000; i++) {
			try {
				sleep(100);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			if(n.updateAndCheck(150))
				break;
		}
		System.out.println("T1:" + "TERMINATED");
	}
	
}

