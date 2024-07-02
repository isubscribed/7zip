function TrowIfLastError {
    param( [string] $Message = "Operation failed." )
    $errorCode = $LASTEXITCODE
    if ($errorCode) {
        $host.SetShouldExit($errorCode);
        throw $Message
    }  
}