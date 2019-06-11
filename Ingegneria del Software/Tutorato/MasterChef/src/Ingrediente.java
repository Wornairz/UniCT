
public class Ingrediente extends Pietanza { //Leaf
	
	private String nome;
	private int quantita;
	private int calorie;

	public Ingrediente(String nome, int quantita, int calorie) {
		super();
		this.nome = nome;
		this.quantita = quantita;
		this.calorie = calorie;
	}


	@Override
	public Pietanza add(Pietanza p) {
		throw new RuntimeException("Il metodo add() non è definito per un ingrediente");
	}


	@Override
	public Pietanza remove(Pietanza p) {
		throw new RuntimeException("Il metodo remove() non è definito per un ingrediente");
	}


	@Override
	public void mostra(String identazione) {
		System.out.println(identazione + "- " + quantita + " gr di " + nome + " (" + calcolaCalorie() + " calorie)");
	}

	@Override
	public int calcolaCalorie() {
		return (int) (((double) calorie/100)*quantita);
	}
	
	public String getNome() {
		return nome;
	}

	public void setNome(String nome) {
		this.nome = nome;
	}

	public int getQuantita() {
		return quantita;
	}

	public void setQuantita(int quantita) {
		this.quantita = quantita;
	}

	public int getCalorie() {
		return calorie;
	}

	public void setCalorie(int calorie) {
		this.calorie = calorie;
	}


}
