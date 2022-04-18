class Renderer {
    constructor() {
        this.meshes = [];
    }

    drawChunk(chunk) {
        this.meshes.push(chunk.mesh);
    }

    render(camera) {
        for (let iMesh in this.meshes) {
            const mesh = this.meshes[iMesh];
            const cameraViewX = camera.position.x - WINDOW_WIDTH / 2;
            const cameraViewZ = camera.position.z - WINDOW_HEIGHT / 2;
            const meshX = ParseInt(mesh.position.x) - cameraViewX;
            const meshZ = ParseInt(mesh.position.z) - cameraViewZ;
            ctx.putImageData(mesh.imgData, meshX, meshZ);
        }
        this.meshes = [];
    }
}