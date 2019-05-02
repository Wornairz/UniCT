import java.util.ArrayList;
import java.util.List;
import java.util.Random;

public class Giocatore {
	public int id;
	public String nome;
	public List<Equip> equipaggiamento;
	
	public Giocatore(String nome) {
		Random r = new Random();
		id = r.nextInt(100);
		this.nome = nome;
		equipaggiamento = new ArrayList<>();
	}
	
	public void addEquip(Equip e) {
		equipaggiamento.add(e);
	}
	
	@Override
	public String toString() {
		String output = "";
		output += "ID = " + id;
		output += " Nome = " + nome + "\n";
		return output;
	}
}
