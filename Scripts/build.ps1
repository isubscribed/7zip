param (
    [Parameter(Mandatory)][string] $sln,
    [Parameter(Mandatory)][string] $configuration,
    [Parameter(Mandatory)][string] $platform,
    [string] $buildNumber = "0000"
)

. $PSScriptRoot\utils.ps1

Write-Host "Building $sln $confgiguration $platform..."
& msbuild @($sln, "/t:Restore;Rebuild", "/p:Configuration=$configuration", "/p:Platform=`"$platform`"", "/p:GithubBuildNumber=$buildNumber", "/m", "/nr:false")
TrowIfLastError "Building $sln $confgiguration $platform failed."
Write-Host "Building $sln $confgiguration $platform done."
