import java.util.Optional;

public class Visualizer {
	
	Optional<Integer> somma;
	Optional<Integer> conta;
	
	public Visualizer() {
		somma = conta = Optional.ofNullable(null);
	}

	public void setSum(int somma) {
		this.somma = Optional.of(somma);
	}

	public void setCount(int conta) {
		this.conta = Optional.of(conta);
	}
	
	public void show() {
		System.out.println("Somma : " + (somma.isPresent() ? somma.get() : "non presente"));
		System.out.println("N° elementi : " + (conta.isPresent() ? conta.get() : "non presente"));
	}
	
}
