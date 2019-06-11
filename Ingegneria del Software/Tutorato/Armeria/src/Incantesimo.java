import java.util.List;

public abstract class Incantesimo implements Spada { //Decorator

	protected Spada s;
	
	Incantesimo(Spada s){
		this.s = s;
	}
	
	@Override
	public String getNome() {
		return s.getNome();
	}

	@Override
	public int getDanno() {
		return s.getDanno();
	}

	@Override
	public List<String> getEffetti() {
		return s.getEffetti();
	}

	@Override
	public String toString() {
		return getNome() + " " + ": atk " + getDanno() + " ";
	}
	
}
