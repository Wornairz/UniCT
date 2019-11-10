
public class MainClass {

	public static void main(String[] args) {
		Mediator m = new ConcreteMediator();
		
		m.show();
		
		m.loadValues();
		m.show();
	}

}
