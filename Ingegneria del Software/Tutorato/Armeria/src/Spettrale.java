import java.util.List;

public class Spettrale extends Incantesimo { // ConcreteDecorator

	Spettrale(Spada s) {
		super(s);
	}
	
	@Override
	public int getDanno() {
		return super.getDanno() + 1;
	}
	
	@Override
	public String getNome() {
		return super.getNome() + " spettrale";
	}
	
	@Override
	public List<String> getEffetti() {
		List<String> effetti = super.getEffetti();
		effetti.add("spettrale");
		return effetti;
	}

}
