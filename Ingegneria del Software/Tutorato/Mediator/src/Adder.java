import java.util.List;

public class Adder extends Collegue {

	int sum;
	
	public Adder(Mediator m) {
		super(m);
	}
	
	public void adda(List<Integer> list) {
		sum = list.stream().mapToInt(x -> x).sum();
		completed("sum");
	}
	
	public int getSum() {
		return sum;
	}

}
