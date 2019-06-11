import java.util.ArrayList;
import java.util.List;

public class Preparato extends Pietanza { //Composite

	private String nome;
	private List<Pietanza> ingredienti;
	
	
	public Preparato(String nome) {
		super();
		this.nome = nome;
		ingredienti = new ArrayList<>();
	}
	
	

	@Override
	public Pietanza add(Pietanza p) {
		ingredienti.add(p);
		return this;
	}



	@Override
	public Pietanza remove(Pietanza p) {
		ingredienti.remove(p);
		return this;
	}



	@Override
	public void mostra(String identazione) {
		System.out.println(identazione + "#" + nome);
		for(Pietanza p : ingredienti)
			p.mostra(identazione + "\t");
		System.out.println(identazione + "Calorie totali: " + calcolaCalorie());
	}

	@Override
	public int calcolaCalorie() {
		return ingredienti.stream().mapToInt(p -> p.calcolaCalorie()).sum();
	}
	
	public String getNome() {
		return nome;
	}

	public void setNome(String nome) {
		this.nome = nome;
	}
	
}
