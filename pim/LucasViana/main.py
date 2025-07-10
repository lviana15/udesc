from numpy.typing import NDArray
from collections import deque
import plotly.graph_objects as go
import plotly.express as px
import numpy as np
import pickle


# Constantes com distancias para vizinhos
# Evitando recalcular em cada chamada

# Equivalente C6 para 3D
C6_OFFSETS = [
    (-1, 0, 0),
    (1, 0, 0),
    (0, -1, 0),
    (0, 1, 0),
    (0, 0, -1),
    (0, 0, 1),
]

# Equivalente C8 para 3D
C26_OFFSETS = [
    (dx, dy, dz)
    for dx in [-1, 0, 1]
    for dy in [-1, 0, 1]
    for dz in [-1, 0, 1]
    if (dx, dy, dz) != (0, 0, 0)
]


# Retorna vizinhos do 'voxel' considerando os limites passados como parametro
def neighbors(
    voxel: tuple[int, int, int],
    shape: tuple[int, int, int],
    offsets: list[tuple[int, int, int]],
) -> list[tuple[int, int, int]]:
    M, N, P = shape
    x, y, z = voxel

    neighbors = [
        (x + dx, y + dy, z + dz)
        for dx, dy, dz in offsets
        if 0 <= x + dx < M and 0 <= y + dy < N and 0 <= z + dz < P
    ]

    return neighbors


# Retorna
# labeled_volume: matriz 3D com rotulo voxels rotulados por grupo
# groups: dicionario com tamanho de cada grupo
def segment_groups(
    volume: NDArray[np.floating],
    target_value: float,
    offsets: list[tuple[int, int, int]],
) -> tuple[NDArray[np.int32], dict[int, int]]:
    M, N, P = volume.shape
    labeled_volume = np.zeros_like(volume, dtype=np.int32)
    label_id = 1
    groups: dict[int, int] = {}

    for x in range(M):
        for y in range(N):
            for z in range(P):
                if volume[x, y, z] == target_value and labeled_volume[x, y, z] == 0:
                    # Quando encontra um voxel sem tipo ainda, realiza BFS pra encontrar o grupo
                    # de voxels conectados com o mesmo valor
                    queue = deque([(x, y, z)])
                    current_component = [(x, y, z)]
                    labeled_volume[x, y, z] = label_id

                    while queue:
                        vx, vy, vz = queue.popleft()
                        for nx, ny, nz in neighbors((vx, vy, vz), (M, N, P), offsets):
                            if (
                                volume[nx, ny, nz] == target_value
                                and labeled_volume[nx, ny, nz] == 0
                            ):
                                labeled_volume[nx, ny, nz] = label_id
                                queue.append((nx, ny, nz))
                                current_component.append((nx, ny, nz))

                    size = len(current_component)

                    if size > 1:
                        groups[label_id] = size
                        label_id += 1
                    else:
                        # Nao considera grupos de tamanho 1
                        for cx, cy, cz in current_component:
                            labeled_volume[cx, cy, cz] = 0

    return labeled_volume, groups


# Retorna total de celulas, somando tamanho de todos grupos rotulados
def total_volume_size(groups: dict[int, int]) -> int:
    return sum(groups.values())


# Retorna matriz 3D apenas com o maior agrupamento
def extract_largest_group(
    labeled_volume: NDArray[np.int32],
    component_sizes: dict[int, int],
    target_value: float,
) -> NDArray[np.floating]:
    if not component_sizes:
        raise ValueError("No valid clusters found.")

    largest_label = max(component_sizes, key=lambda k: component_sizes[k])

    volume = np.zeros_like(labeled_volume, dtype=np.float32)
    volume[labeled_volume == largest_label] = target_value

    return volume


# Renderiza o volume 3D usando Plotly
# Deve abrir no navegador e pode demorar
def render_volume(volume: NDArray):
    x, y, z = np.meshgrid(
        np.arange(volume.shape[0]),
        np.arange(volume.shape[1]),
        np.arange(volume.shape[2]),
        indexing="ij",
    )

    fig = go.Figure(
        data=go.Volume(
            x=x.flatten(),
            y=y.flatten(),
            z=z.flatten(),
            value=volume.flatten(),
            opacity=0.1,
            surface_count=20,
        )
    )
    fig.show()


def main():
    offsets = C26_OFFSETS  # Usando C26 para segmentação

    # Carrega a matriz de volume do arquivo
    with open("volume_TAC", "rb") as f:
        volume = pickle.load(f)

    # Calcula numero de grupos e seus tamanhos, gerando volume com todas celulas
    plorifer_volume, plorifer_groups = segment_groups(volume, 255, offsets)
    quiescent_volume, quiescent_groups = segment_groups(volume, 200, offsets)
    necro_volume, necro_groups = segment_groups(volume, 140, offsets)

    # Gera matrizes 3D apenas com maior agrupamento de cada tipo
    largest_plorifer = extract_largest_group(plorifer_volume, plorifer_groups, 255)
    largest_quiescent = extract_largest_group(quiescent_volume, quiescent_groups, 200)
    largest_necro = extract_largest_group(necro_volume, necro_groups, 140)

    # Insere resultados adquiridos em arquivo texto
    with open("resultado.txt", "w") as file:
        file.write("Totais de células por tipo:\n")
        file.write(f"  Proliferativas: {total_volume_size(plorifer_groups):,}\n")
        file.write(f"  Quiescentes: {total_volume_size(quiescent_groups):,}\n")
        file.write(f"  Necróticas: {total_volume_size(necro_groups):,}\n\n")

        file.write("Distribuição dos tamanhos dos agrupamentos:\n")

        file.write("  Proliferativas:\n")
        for label, size in plorifer_groups.items():
            file.write(f"    - Agrupamento {label}: {size} células\n")

        file.write("  Quiescentes:\n")
        for label, size in quiescent_groups.items():
            file.write(f"    - Agrupamento {label}: {size} células\n")

        file.write("  Necróticas:\n")
        for label, size in necro_groups.items():
            file.write(f"    - Agrupamento {label}: {size} células\n")

    # Salva volumes com maior grupamento de cada tipo em arquivos .npy
    np.save("proliferativa.npy", largest_plorifer)
    np.save("quiescente.npy", largest_quiescent)
    np.save("necrotica.npy", largest_necro)

    # Renderiza um dos volumes com o maior agrupamento
    render_volume(largest_plorifer)


main()
