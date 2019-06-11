
public class TestBankAccount {
	private BankAccount ba ;
	public static void main(String[] args) {
		TestBankAccount t = new TestBankAccount();
		t.testInizioPositivo();
		t.testPremium();
		t.testDepositPremium();
		t.testWithdrawNormal();
		t.testWithdrawPremium();
		t.testWithdrawNormalNegative();
		
		
	}
	
	TestBankAccount(){
		ba = new BankAccount(0);
	}
	
	public void testInizioPositivo(){
		ba = new BankAccount(10);
		if(ba.getCredit() == 10)
			System.out.println("SUCCESS testInizioPositivo");
		else
			System.out.println("FAIL testInizioPositivo");
	}
	
	public void testPremium() {
		ba = new BankAccount(0);
		ba.deposit(1000);
		if(ba.isPremium())
			System.out.println("SUCCESS testPremium");
		else
			System.out.println("FAIL testPremium");
	}
	
	public void testDepositPremium() {
		ba = new BankAccount(1000);
		ba.deposit(2000);
		ba.deposit(1000);
		if(ba.getCredit()==4200)
			System.out.println("SUCCESS testDepositPremium");
		else
			System.out.println("FAIL testDepositPremium");
	}
	
	public void testWithdrawNormal() {
		ba = new BankAccount(500);
		if(ba.withdraw(200)==200 && ba.getCredit()==300)
			System.out.println("SUCCESS testWithdrawNormale");
		else
			System.out.println("FAIL testWithdrawNormale");
			
	}
	
	public void testWithdrawPremium() {
		ba = new BankAccount(500);
		ba.deposit(2000);
		if(ba.withdraw(5000) == 5000 && ba.getCredit()==-2400) 
			System.out.println("SUCCESS testWithdrawPremium");
		else
			System.out.println("FAIL testWithdrawPremium");
	}
	
	public void testWithdrawNormalNegative() {
		ba = new BankAccount(500);
		if(ba.withdraw(1000) == 500 && ba.getCredit()==0)
			System.out.println("SUCCESS testWithdrawPremium");
		else
			System.out.println("FAIL testWithdrawPremium");		
	}
}
