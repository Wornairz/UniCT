import java.util.ArrayList;
import java.util.List;

public class ListaUtenti {
	public List<Giocatore> giocatori = new ArrayList<>();
	
	@Override
	public String toString() {
		String output = "";
		for(Giocatore g : giocatori) {
			output += g.toString();
		}
		return output;
	}
}
