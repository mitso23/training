trap cleanup SIGINT EXIT
trap error_handling ERR

cleanup()
{
        popd > /dev/null 2>&1
        exit 0
}

error_handling()
{
        popd > /dev/null 2>&1
        exit 1
}

