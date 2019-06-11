import java.util.ArrayList;
import java.util.List;

public class SpadaBase implements Spada { //ConcreteComponent

	@Override
	public String getNome() {
		return "Spada Base";
	}

	@Override
	public int getDanno() {
		return 10;
	}

	@Override
	public List<String> getEffetti() {
		return new ArrayList<String>();
	}
}
