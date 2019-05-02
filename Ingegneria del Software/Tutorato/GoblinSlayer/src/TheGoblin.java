
public class TheGoblin extends Pelleverde implements Goblin {

	@Override
	public void tiraFreccia(int damage) {
		super.scagliaPezzoDiLegno(damage*10);
	}

}
