import java.util.List;

public class Infuocata extends Incantesimo { // ConcreteDecorator

	Infuocata(Spada s) {
		super(s);
	}

	@Override
	public int getDanno() {
		return super.getDanno() + 5;
	}
	
	@Override
		public String getNome() {
			return super.getNome() + " infuocata";
		}
	
	@Override
	public List<String> getEffetti() {
		List<String> effetti = super.getEffetti();
		effetti.add("fuoco");
		return effetti;
	}
}
