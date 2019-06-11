import java.util.ArrayList;
import java.util.List;

public class SpadaPesante implements Spada { //ConcreteComponent

	@Override
	public String getNome() {
		return "Spada Pesante";
	}

	@Override
	public int getDanno() {
		return 15;
	}

	@Override
	public List<String> getEffetti() {
		return new ArrayList<String>();
	}
	
}
