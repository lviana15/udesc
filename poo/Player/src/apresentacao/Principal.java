package src.apresentacao;

import src.dados.Artist;
import src.dados.Song;
import src.dados.User;
import src.negocio.PlayerSystem;

import java.time.LocalDate;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Principal {
    private static final PlayerSystem playerSystem = new PlayerSystem();

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        loginMenu(scanner);
    }

    private static void menu(Scanner scanner) {
        while (true) {
            System.out.println("=== Menu Principal ===");
            System.out.println("1. Carregar uma música");
            System.out.println("2. Adicionar autor");
            System.out.println("3. Listar todas as músicas");
            System.out.println("4. Listar todos os artistas (autores)");
            System.out.println("5. Listar todas as playlists");
            System.out.println("6. Adicionar música a uma playlist");
            System.out.println("7. Remover música de uma playlist");
            System.out.println("8. Logout e Sair");
            System.out.print("Escolha uma opção: ");

            int choice = scanner.nextInt();
            scanner.nextLine();

            switch (choice) {
                case 1:
                    uploadSong(scanner);
                    break;
                case 2:
                    addArtist(scanner);
                    break;
                case 3:
                    playerSystem.listSongs();
                    break;
                case 4:
                    playerSystem.listArtists();
                    break;
                case 5:
                    playerSystem.listPlaylists();
                    break;
                case 6:
                    addSongToPlaylist(scanner);
                    break;
                case 7:
                    removeSongFromPlaylist(scanner);
                    break;
                case 8:
                    System.out.println("Saindo. Até logo!");
                    scanner.close();
                    System.exit(0);
                default:
                    System.out.println("Opção inválida. Por favor, tente novamente.");
            }
        }
    }

    private static void uploadSong(Scanner scanner) {
        System.out.println("Digite título:");
        String title = scanner.nextLine();
        System.out.println("Digite data (YYYY-MM-DD):");

        LocalDate date;
        try {
            String userInput = scanner.nextLine();
            date = LocalDate.parse(userInput);
        } catch (Exception e) {
            System.out.println("Formato inválido.");
            return;
        }

        Song newSong = new Song(title, date);
        List<Integer> artists = new ArrayList<>();

        boolean selectingAuthors = true;
        while (selectingAuthors) {
            playerSystem.printTable("artists");

            System.out.println("Escolha um autor pelo ID (ou digite 'stop' para parar): ");
            String userInput = scanner.nextLine();

            if (userInput.equalsIgnoreCase("stop")) {
                selectingAuthors = false;
            } else {
                try {
                    int authorId = Integer.parseInt(userInput);
                    artists.add(authorId);
                } catch (NumberFormatException e) {
                    System.out.println("ID do autor inválido. Tente novamente.");
                }
            }
        }

        playerSystem.uploadSong(newSong, artists);
    }

    private static void addArtist(Scanner scanner) {
        System.out.print("Digite o nome do artista: ");
        String name = scanner.nextLine();

        System.out.print("Digite a biografia do artista: ");
        String bio = scanner.nextLine();

        Artist newArtist = new Artist(name, bio);
        playerSystem.addArtist(newArtist);
    }

    private static void addSongToPlaylist(Scanner scanner) {
        playerSystem.printTable("playlists");

        System.out.println("Digite o ID da playlist:");
        int playlistId;
        try {
            playlistId = Integer.parseInt(scanner.nextLine());
        } catch (NumberFormatException e) {
            System.out.println("ID da playlist inválido. Tente novamente.");
            return;
        }

        System.out.println("Digite o ID da música que deseja adicionar:");
        int songId;
        try {
            songId = Integer.parseInt(scanner.nextLine());
        } catch (NumberFormatException e) {
            System.out.println("ID da música inválido. Tente novamente.");
            return;
        }

        playerSystem.addSongToPlaylist(playlistId, songId);
    }

    private static void removeSongFromPlaylist(Scanner scanner) {
        playerSystem.printTable("playlists");

        System.out.println("Digite o ID da playlist:");
        int playlistIdRemove;
        try {
            playlistIdRemove = Integer.parseInt(scanner.nextLine());
        } catch (NumberFormatException e) {
            System.out.println("ID da playlist inválido. Tente novamente.");
            return;
        }

        System.out.println("Digite o ID da música que deseja remover:");
        int songIdRemove;
        try {
            songIdRemove = Integer.parseInt(scanner.nextLine());
        } catch (NumberFormatException e) {
            System.out.println("ID da música inválido. Tente novamente.");
            return;
        }

        playerSystem.removeSongFromPlaylist(playlistIdRemove, songIdRemove);
    }

    private static void loginMenu(Scanner scanner) {
        while (true) {
            System.out.println("=== Menu de Login/Registro ===");
            System.out.println("1. Login");
            System.out.println("2. Registrar uma nova conta");
            System.out.println("3. Sair");
            System.out.print("Escolha uma opção: ");

            int choice = scanner.nextInt();
            scanner.nextLine();

            switch (choice) {
                case 1:
                    while (true) {
                        System.out.print("Digite o nome de usuário (ou 'exit' para sair): ");
                        String username = scanner.nextLine();

                        if (username.equalsIgnoreCase("exit")) {
                            System.out.println("Saindo do login.");
                            break;
                        }

                        System.out.print("Digite a senha: ");
                        String password = scanner.nextLine();

                        if (playerSystem.login(username, password)) {
                            System.out.println("Usuário logado");
                            menu(scanner);
                        } else {
                            System.out.println("Nome de usuário ou senha incorretos. Tente novamente.");
                        }
                    }
                    break;
                case 2:
                    System.out.print("Digite seu nome: ");
                    String name = scanner.nextLine();

                    System.out.print("Digite um nome de usuário: ");
                    String username = scanner.nextLine();

                    System.out.print("Digite uma senha: ");
                    String password = scanner.nextLine();

                    User newUser = new User(name, username, password);
                    playerSystem.registerUser(newUser);

                    break;
                case 3:
                    System.out.println("Saindo. Até logo!");
                    scanner.close();
                    System.exit(0);
                default:
                    System.out.println("Opção inválida. Por favor, tente novamente.");
            }
        }
    }
}
