
public class MainChef {

	public static void main(String[] args) {
		Pietanza pastaAlPistacchio = Ricettario.getPreparato("Pasta al pistacchio")
				.add(Ricettario.getIngrediente("pasta", 250))
				.add(Ricettario.getIngrediente("pistacchio", 30))
				.add(Ricettario.getIngrediente("panna", 80))
				.add(Ricettario.getIngrediente("pancetta", 50));
		
		pastaAlPistacchio.mostra("");
		
		System.out.println("");
		
		Pietanza carnepatate = Ricettario.getPreparato("Carne e Patate")
				.add(Ricettario.getIngrediente("carne", 100))
				.add(Ricettario.getIngrediente("patate", 100));
				
		Pietanza risoCarnePatate = Ricettario.getPreparato("Risotto con carne e patate")
				.add(Ricettario.getIngrediente("riso", 300))
				.add(carnepatate);
		
		risoCarnePatate.mostra("");
	}

}
