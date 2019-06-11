
public class Counter {
	private static Counter c = new Counter();
	protected int x = 0;
	
	private Counter() {
		
	}
	
	public void printx() {
		System.out.println(x);
	}
	
	public static Counter getInstance() {
		return c;
	}
	
}
