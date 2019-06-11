import java.util.List;

public class Avvelenata extends Incantesimo { // ConcreteDecorator

	Avvelenata(Spada s) {
		super(s);
	}

	@Override
	public int getDanno() {
		return super.getDanno() + 2;
	}
	
	@Override
	public String getNome() {
		return super.getNome() + " avvelenata";
	}
	
	@Override
	public List<String> getEffetti() {
		List<String> effetti = super.getEffetti();
		effetti.add("veleno");
		return effetti;
	}
	
}
