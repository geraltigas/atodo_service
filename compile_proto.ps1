$currentDir = Get-Location
$protoDir = Join-Path -Path $currentDir -ChildPath "grpc"
$outputDir = Join-Path -Path $currentDir -ChildPath "src\grpc"
$protocPath = ".\cmake-build-release\bin\protoc.exe"
$grpcCppPluginPath = ".\cmake-build-release\bin\grpc_cpp_plugin.exe"
$protoIncludeDir = ".\cmake-build-release\protos"

if (-not (Test-Path -Path $outputDir)) {
    New-Item -ItemType Directory -Path $outputDir
}

$protoFiles = Get-ChildItem -Path $protoDir -Filter *.proto

foreach ($file in $protoFiles) {
    $protoPath = $file.FullName
    $outPath = $outputDir

    & $protocPath "--proto_path=$protoIncludeDir" "--proto_path=$protoDir" "--cpp_out=$outPath" "--grpc_out=$outPath" "--plugin=protoc-gen-grpc=$grpcCppPluginPath" $protoPath

    if ($LASTEXITCODE -ne 0) {
        Write-Error "Failed to compile $protoPath"
    } else {
        Write-Host "Successfully compiled $protoPath"
    }
}