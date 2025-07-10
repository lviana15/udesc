package persistencia;

import dados.Pessoa;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class PessoaDAO {
    private PreparedStatement sqlInsert;
    private PreparedStatement sqlUpdate;
    private PreparedStatement sqlSelectOne;
    private PreparedStatement sqlSelectAll;
    private PreparedStatement nextId;

    private PessoaDAO() {
        Connection conn = Conexao.getConexao();
        try {
            sqlInsert = conn.prepareStatement("INSERT INTO pessoa (id, nome, cpf, telefone) VALUES (?, ?, ?, ?)");
            sqlSelectOne = conn.prepareStatement("SELECT * FROM pessoa WHERE id = ?");
            nextId = conn.prepareStatement("SELECT nextval('id_pessoa')");
        } catch (SQLException e) {
            e.getMessage();
        }
    }

    public void insertPessoa(Pessoa p) {
        try{
            ResultSet id = nextId.executeQuery();
            id.next();
            int idPessoa = id.getInt(1);
            sqlInsert.setInt(1, idPessoa);
            sqlInsert.setString(2, p.getNome());
            sqlInsert.setString(3, p.getCpf());
            sqlInsert.setString(4, p.getTelefone());

            sqlInsert.executeUpdate();
        } catch (SQLException e) {
            e.getMessage();
        }
    }
}
