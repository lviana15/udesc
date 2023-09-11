
public class ContaBancaria {
    private int cpf;
    private float saldo;

    public float sacar(float valor) {
        saldo = saldo - valor;
        return saldo;
    }

    public String gerarExtrato() {
        return "Saldo: " +saldo;
    }

    public setCpf(int cpf){
        this.cpf = cpf;
    }

    public int getCpf() {
        return cpf;
    }

    public void setSaldo(float saldo) {
        this.saldo = saldo;
    }

    public float getSaldo() {
        return saldo;
    }
}
