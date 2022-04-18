class World {
    constructor(noiseGenerator) {
        this.chunkManger = new ChunkManager(noiseGenerator);
        // number of chunks to render vertically and horizontally
        this.renderDistance = 10;
        this.loadDistance = 2;
    }

    draw(renderer) {
        const chunks = this.chunkManger.chunks;
        for (let iChunk in chunks) {
            const chunk = chunks[iChunk];
            const chunkElement = chunk.element;
            chunkElement.draw(renderer);
        }
    }

    loadChunks(camera) {
        let isBuffered = false;
        let cameraX = parseInt(camera.position.x / CHUNK_SIZE);
        let cameraZ = parseInt(camera.position.z / CHUNK_SIZE);
        for (let i = 0; i < this.loadDistance; i++) {
            const minX = Math.max(cameraX - i, 0);
            const minZ = Math.max(cameraZ - i, 0);
            const maxX = cameraX + i;
            const maxZ = cameraZ + i;
            for (let x = minX; x < maxX; x++) {
                for (let z = minZ; z < maxZ; z++) {
                    this.chunkManger.load(x * CHUNK_SIZE, z * CHUNK_SIZE);
                    isBuffered = this.chunkManger.addToBuffer(x * CHUNK_SIZE, z * CHUNK_SIZE);
                }
            }

            if (isBuffered) {
                break;
            }
        }

        if(!isBuffered) {
            this.loadDistance++;
        }

        if (this.loadDistance > this.renderDistance) {
            this.loadDistance = 2;
        }
    }
}