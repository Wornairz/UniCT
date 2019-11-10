import java.util.List;

public class Counter extends Collegue{

	int count;
	
	public Counter(Mediator m) {
		super(m);
	}
	
	public void conta(List<Integer> list) {
		count = (int) list.stream().count();
		completed("count");
	}
	
	public int getCount() {
		return count;
	}

}
